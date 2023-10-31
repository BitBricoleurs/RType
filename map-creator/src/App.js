// src/App.js
import React, { useState } from 'react';
import Toolbar from './components/Toolbar';
import Map from './components/Map';
import './App.css';

function App() {
    const [selectedCard, setSelectedCard] = useState(null);
    const [mapItems, setMapItems] = useState([]);
    const handleDeleteItem = (itemToDelete) => {
        setMapItems(prevItems => prevItems.filter(item => item !== itemToDelete));
    };

    const handleMapClick = (event) => {
        if (selectedCard) {
            const rect = event.target.getBoundingClientRect();
            const newItem = {
                ...selectedCard,
                x: event.clientX - rect.left - (selectedCard.rect.width * selectedCard.scale / 2),
                y: event.clientY - rect.top - (selectedCard.rect.height * selectedCard.scale / 2),
            };
            setMapItems([...mapItems, newItem]);
        }
    };

    return (
        <div className="App">
            <Map onMapClick={handleMapClick} mapItems={mapItems} onDeleteItem={handleDeleteItem} />
            <Toolbar setSelectedCard={setSelectedCard} selectedCard={selectedCard} />
        </div>
    );
}

export default App;
