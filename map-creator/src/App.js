import entities from './data.json';
import parallax from './parallaxData.json'
import React, {useEffect, useState} from 'react';
import { Position, Toaster, Intent } from "@blueprintjs/core";
import Toolbar from './components/Toolbar';
import Map from './components/Map';
import ParallaxModal from './components/ParallaxModal';
import './App.css';
const {ipcRenderer} = window.require('electron');

const AppToaster = Toaster.create({
    className: "recipe-toaster",
    position: Position.TOP,
}, document.body );

function App() {

    const [isAnimating, setIsAnimating] = useState(false);

    const showSuccessToast = (message) => {
        AppToaster.show({ message, intent: Intent.SUCCESS });
    };

    const showErrorToast = (message) => {
            AppToaster.show({ message, intent: Intent.DANGER });
    };

    const [selectedCard, setSelectedCard] = useState(null);
    const [selectedParallax, setSelectedParallax] = useState(null);
    const [mapItems, setMapItems] = useState([]);
    const [backgroundImages, setBackgroundImages] = useState([]);
    const [isParallaxModalOpen, setIsParallaxModalOpen] = useState(false);

    const handleDeleteItem = (itemToDelete) => {
        setMapItems(prevItems => prevItems.filter(item => item !== itemToDelete));
    };

    const handlePowerUp = (itemToPowerUp) => {
        itemToPowerUp.powerUp = !itemToPowerUp.powerUp;
    }

    const handleSelectLayer = (parallaxData) => {
        setIsParallaxModalOpen(true);
    };

    const handleCloseModal = () => {
        setIsParallaxModalOpen(false);
    };

    const handleMapClick = (event) => {
        const x = event.pageX;
        const y = event.pageY;
        console.log('Map clicked', x, y);

        if (selectedCard) {
            const newItem = {
                ...selectedCard,
                x: x - selectedCard.rect.width / 2,
                y: y - selectedCard.rect.height / 2,
            };
            setMapItems([...mapItems, newItem]);
        } else if (selectedParallax) {
            const newParallaxItem = {
                ...selectedParallax,
                x: x - selectedParallax.rect.width / 2,
                y: y - selectedParallax.rect.height / 2,
            };
            setBackgroundImages([...backgroundImages, newParallaxItem]);
        }
    };

    function placeParallaxEntities(parallaxData) {
        if (parallaxData.isBackgroundEnabled) {
            const mapWidth = 192000;
            const entityWidth = parallaxData.rect.width * parallaxData.scale;
            const entitiesToPlace = Math.ceil(mapWidth / entityWidth);

            for (let i = 0; i < entitiesToPlace; i++) {
                backgroundImages.push({
                    ...parallaxData,
                    x: i * entityWidth,
                    y: 0
                });
            }

        }
    }

    const handleParallaxRightClick = (parallaxItem) => {
        setSelectedParallax(parallaxItem);
        setIsParallaxModalOpen(true);
    };

    const onDeleteParallax = (parallaxToDelete) => {
        if (parallaxToDelete.isBackgroundEnabled) {
        setBackgroundImages(prevImages => prevImages.filter(bg => bg.id !== parallaxToDelete.id));
        } else {
        setBackgroundImages(prevImages => prevImages.filter(bg => bg !== parallaxToDelete));
        }
    };

    useEffect(() => {
        const handleKeyDown = (event) => {
            if (event.key === 's' || event.key === 'S') {
                event.preventDefault();
            }
        };

        window.addEventListener('keydown', handleKeyDown);

        return () => {
            window.removeEventListener('keydown', handleKeyDown);
        };
    }, [mapItems, backgroundImages]);

    useEffect(() => {
        const handleSaveSuccess = (_, args) => {
            showSuccessToast('Save was successful!');
        };

        const handleSaveFailed = (_, args) => {
            showErrorToast('Save failed, please try again.');
        };

        const handleFileContent = (_, content) => {
            handleLoad(content);
            showSuccessToast('Load was successful!');
        };

        const handleFileReadFailed = (_, args) => {
            showErrorToast('Failed to read the file, please try again.');
        };

        const handleFileDialogOpenFailed = (_, args) => {
            showErrorToast('Failed to open the file dialog, please try again.');
        };

        const handleOpen = () => {
            ipcRenderer.send('open-file-dialog');
        };

        ipcRenderer.on('menu-action', (event, action) => {
            if (action === 'new') {
            }
            if (action === 'save') {
                handleSave();
            }
            if (action === 'open') {
                handleOpen();
            }
        });

        ipcRenderer.on('save-success', handleSaveSuccess);
        ipcRenderer.on('save-failed', handleSaveFailed);
        ipcRenderer.on('file-content', handleFileContent);
        ipcRenderer.on('file-read-failed', handleFileReadFailed);
        ipcRenderer.on('file-dialog-open-failed', handleFileDialogOpenFailed);

        return () => {
            ipcRenderer.removeAllListeners('menu-action');
            ipcRenderer.removeListener('save-success', handleSaveSuccess);
            ipcRenderer.removeListener('save-failed', handleSaveFailed);
            ipcRenderer.removeListener('file-content', handleFileContent);
            ipcRenderer.removeListener('file-read-failed', handleFileReadFailed);
            ipcRenderer.removeListener('file-dialog-open-failed', handleFileDialogOpenFailed);
        };
    }, [showSuccessToast, showErrorToast]);


    const getEntityByNameEntities = (name) => {
        const entity = entities.find(entity => entity.name === name);

        return entity;
    }

    const getEntityByNameParallax = (id) => {
        const entity = parallax.find(entity => entity.id === id);

        return entity;
    }

    const handleSave = () => {
        const groupedImages = backgroundImages.reduce((acc, img) => {
            if (img.isBackgroundEnabled) {
                if (!acc[img.id]) {
                    acc[img.id] = [];
                }
                acc[img.id].push(img);
            }
            return acc;
        }, {});

        const selectedImages = Object.values(groupedImages).reduce((acc, group) => {
            return acc.concat(group.slice(0, 2));
        }, []);

        const parallaxWithBackground = selectedImages.map(image => ({
            tick: 1,
            type: image.id,
            layer: image.layer,
            isLooping: image.isLooping,
            velocity: {
                x: parseFloat(image.velocity.x).toFixed(1),
                y: parseFloat(image.velocity.y).toFixed(1)
            },
            position: {
                x: Math.round(image.x),
                y: Math.round(image.y)
            },
            isBackgroundEnabled: image.isBackgroundEnabled,
        }));

        const otherParallaxItems = backgroundImages.filter(image => !image.isBackgroundEnabled).map(image => ({
            tick: image.velocity.x === 0 ? 1 : Math.round(image.x / Math.abs(image.velocity.x)),
            type: image.id,
            layer: image.layer,
            isLooping: image.isLooping,
            velocity : {
                x: parseFloat(image.velocity.x).toFixed(1),
                y: parseFloat(image.velocity.y).toFixed(1)
            },
            position: {
                x: 2000,
                y: Math.round(image.y)
            },
            isBackgroundEnabled: image.isBackgroundEnabled,
        }));

        const mobs = mapItems.map(item => ({
            tick: item.velocity.x === 0 ? 1 : Math.round(item.x /  Math.abs(item.velocity.x)),
            mobType: item.name,
            velocity: {
                x: item.velocity.x.toFixed(1),
                y: item.velocity.y.toFixed(1),
            },
            position: {
                x: 2000,
                y: Math.round(item.y),
            },
            dropPowerUp: item.powerUp,
        }));

        mapItems.forEach(item => {
            console.log('MobType after', item.name);
        }
        );

        const sortedMobs = mobs.sort((a, b) => a.tick - b.tick);

        const enhancedMobs = sortedMobs.map((mob, index, array) => {
            const isLastMob = index === array.length - 1;
            return { ...mob, isLastMob };
        });
        const combinedParallaxItems = [...parallaxWithBackground, ...otherParallaxItems];

        mapItems.forEach(item => {
                console.log('MobType before', item.name);
            }
        );

        const formattedData = {
            parallax: combinedParallaxItems,
            mobs: enhancedMobs
        };

        let formattedJson = JSON.stringify(formattedData, null, 2);

        formattedJson = formattedJson.replace(/"(-?\d+\.\d+)"/g, (match, p1) => {
            return `${parseFloat(p1).toFixed(1)}`;
        });

        formattedJson = formattedJson.replace(/},/g, '},\n');

        ipcRenderer.send('save-dialog', formattedJson);
    };


    const handleLoad = (content) => {
        try {
            const data = JSON.parse(content);

            const mobsTabs = data.mobs.map(mob => {
                const entity = getEntityByNameEntities(mob.mobType);

                return {
                    ...mob,
                    x: Math.abs(mob.velocity.x) * mob.tick,
                    y: mob.position.y,
                    powerUp: mob.dropPowerUp,
                    src: entity ? entity.src : undefined,
                    rect: entity ? entity.rect : undefined,
                    scale: entity ? entity.scale : undefined,
                };
            });


            const backgroundImagesExtended = data.parallax.flatMap(image => {
                const entity = getEntityByNameParallax(image.type);

                if (image.isBackgroundEnabled && image.position.x === 0 && image.position.y === 0) {
                    return Array.from({ length: 100 }, (_, i) => ({
                        ...image,

                        x: image.position.x + (i * entity.rect.width),
                        y: image.position.y,
                        id : image.type,
                        path: entity ? entity.path : undefined,
                        rect: entity ? entity.rect : undefined,
                        scale: entity ? entity.scale : undefined,
                    }));
                } else {
                    return [{
                        ...image,
                        x: Math.abs(image.velocity.x) * image.tick,
                        y: image.position.y,
                        id : image.type,
                        path: entity ? entity.path : undefined,
                        rect: entity ? entity.rect : undefined,
                        scale: entity ? entity.scale : undefined,
                    }];
                }
            });

            setMapItems(mobsTabs);
            setBackgroundImages(backgroundImagesExtended);

        } catch (error) {
            console.error(error);
            showErrorToast('Failed to load the file, please try again.');
        }
    }

    return (
        <div className="App">
            <Map
                onMapClick={handleMapClick}
                mapItems={mapItems}
                onDeleteItem={handleDeleteItem}
                backgroundImages={backgroundImages}
                selectedCard={selectedCard}
                selectedParallax={selectedParallax}
                onParallaxRightClick={handleParallaxRightClick}
                OnPowerUp={handlePowerUp}
                isAnimating={isAnimating}
            />
            <Toolbar
                setSelectedCard={setSelectedCard}
                selectedCard={selectedCard}
                setSelectedParallax={setSelectedParallax}
                selectedParallax={selectedParallax}
                onSelectParallax={handleSelectLayer}
                isAnimating={isAnimating}
                toggleAnimation={() => setIsAnimating(!isAnimating)}
            />

            {isParallaxModalOpen && (
                <ParallaxModal
                    parallaxData={selectedParallax}
                    onClose={handleCloseModal}
                    setSelectedParallax={setSelectedParallax}
                    placeParallaxEntities={placeParallaxEntities}
                    onDeleteParallax={onDeleteParallax}
                />
            )}
        </div>
    );
}

export default App;
