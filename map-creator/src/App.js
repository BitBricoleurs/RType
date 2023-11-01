import React, { useState } from 'react';
import Toolbar from './components/Toolbar';
import Map from './components/Map';
import ParallaxModal from './components/ParallaxModal';
import './App.css';

function App() {
    const [selectedCard, setSelectedCard] = useState(null);
    const [selectedParallax, setSelectedParallax] = useState(null);
    const [mapItems, setMapItems] = useState([]);
    const [backgroundImages, setBackgroundImages] = useState([]);
    const [isParallaxModalOpen, setIsParallaxModalOpen] = useState(false); // État pour gérer l'ouverture de la modale

    const handleDeleteItem = (itemToDelete) => {
        setMapItems(prevItems => prevItems.filter(item => item !== itemToDelete));
    };

    const handleSelectLayer = (parallaxData) => {
        setIsParallaxModalOpen(true); // Ouvrir la modale
    };

    const handleCloseModal = () => {
        setIsParallaxModalOpen(false); // Fermer la modale
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
            const mapWidth = 192000; // Remplacez par la largeur réelle de votre map
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
