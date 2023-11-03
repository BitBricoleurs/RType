import React, {useEffect, useRef, useState} from 'react';
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

    const showSuccessToast = (message) => {
        AppToaster.show({ message, intent: Intent.SUCCESS });
    };

    const showErrorToast = (message) => {
        const showErrorToast = (message) => {
            AppToaster.show({ message, intent: Intent.DANGER });
        };
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
                x: x,
                y: y,
            };
            setMapItems([...mapItems, newItem]);
        } else if (selectedParallax) {
            const newParallaxItem = {
                ...selectedParallax,
                x: x,
                y: y,
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

        ipcRenderer.on('menu-action', (event, action) => {
            if (action === 'new') {
            }
            if (action === 'save') {
                handleSave();
            }
        });

        ipcRenderer.on('save-success', handleSaveSuccess);
        ipcRenderer.on('save-failed', handleSaveFailed);

        return () => {
            ipcRenderer.removeAllListeners('menu-action');
            ipcRenderer.removeListener('save-success', handleSaveSuccess);
            ipcRenderer.removeListener('save-failed', handleSaveFailed);
        };
    }, [mapItems, backgroundImages]);


    const handleSave = () => {
        const enabledBackgroundImages = backgroundImages.filter(img => img.isBackgroundEnabled).slice(0, 2);

        const parallaxWithBackground = enabledBackgroundImages.map(image => ({
            tick: 1,
            type: image.name,
            layer: image.layer,
            isLooping: image.isLooping,
            velocity : {
                x: parseFloat(image.velocity.x).toFixed(1),
                y: parseFloat(image.velocity.y).toFixed(1)
            },
            position: {
                x: image.x,
                y: image.y
            },
            isBackgroundEnabled: image.isBackgroundEnabled
        }));

        const otherParallaxItems = backgroundImages.filter(image => !image.isBackgroundEnabled).map(image => ({
            tick: image.velocity.x === 0 ? 1 : Math.round(image.x / Math.abs(image.velocity.x)),
            type: image.name,
            layer: image.layer,
            isLooping: image.isLooping,
            velocity : {
                x: parseFloat(image.velocity.x).toFixed(1),
                y: parseFloat(image.velocity.y).toFixed(1)
            },
            position: {
                x: 2000,
                y: image.y
            },
            isBackgroundEnabled: image.isBackgroundEnabled
        }));

        const mobs = mapItems.map(item => ({
            tick: item.velocity.x === 0 ? 1 : Math.round(item.x /  Math.abs(item.velocity.x)),
            mobType: item.name,
            velocity : {
                x: item.velocity.x.toFixed(1),
                y: item.velocity.y.toFixed(1),
            },
            position: {
                x: 2000,
                y: item.y
            },

            dropPowerUp: item.powerUp,
        }));
        const combinedParallaxItems = [...parallaxWithBackground, ...otherParallaxItems];

        const formattedData = {
            parallax: combinedParallaxItems,
            mobs: mobs
        };

        let formattedJson = JSON.stringify(formattedData, null, 2);

        formattedJson = formattedJson.replace(/"(-?\d+\.\d+)"/g, (match, p1) => {
            return `${parseFloat(p1).toFixed(1)}`;
        });

        // Optionally add line breaks where you want them
        formattedJson = formattedJson.replace(/},/g, '},\n');

        ipcRenderer.send('save-dialog', formattedJson);
    };


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
            />
            <Toolbar
                setSelectedCard={setSelectedCard}
                selectedCard={selectedCard}
                setSelectedParallax={setSelectedParallax}
                selectedParallax={selectedParallax}
                onSelectParallax={handleSelectLayer}
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
