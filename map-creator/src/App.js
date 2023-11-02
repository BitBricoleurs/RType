import React, {useEffect, useState} from 'react';
import Toolbar from './components/Toolbar';
import Map from './components/Map';
import ParallaxModal from './components/ParallaxModal';
import './App.css';
const {ipcRenderer} = window.require('electron');

function App() {

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
                x: x - (selectedCard.rect.width * selectedCard.scale / 2),
                y: y - (selectedCard.rect.height * selectedCard.scale / 2),
            };
            setMapItems([...mapItems, newItem]);
        } else if (selectedParallax) {
            const newParallaxItem = {
                ...selectedParallax,
                x: x - (selectedParallax.rect.width * selectedParallax.scale / 2),
                y: y - (selectedParallax.rect.height * selectedParallax.scale / 2),
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
        setBackgroundImages(prevImages => prevImages.filter(bg => bg.id !== parallaxToDelete.id));
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
        // Écoutez les messages provenant du processus principal
        ipcRenderer.on('menu-action', (event, action) => {
            if (action === 'new') {
                // Votre logique ici pour 'New'
            }
            if (action === 'save') {
                console.log('Save');
                // Votre logique ici pour 'Open'
            }
            // Traitez d'autres actions ici
        });

        return () => {
            // Nettoyage : retirez l'écouteur lorsque le composant est démonté
            ipcRenderer.removeAllListeners('menu-action');
        };
    }, []);

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
