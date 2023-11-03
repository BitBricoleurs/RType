// src/components/ParallaxEntityList.js
import React from 'react';
import './EntityList.css';
import ParallaxCard from './ParallaxCard';
import parallaxData from '../parallaxData.json';

function ParallaxEntityList({ setSelectedParallax, selectedParallax, onSelectParallax }) {
    return (
        <div className="entity-list">
            {parallaxData.map((parallaxData, index) => (
                <ParallaxCard
                    key={index}
                    src={parallaxData.path}
                    name={parallaxData.name}
                    isSelected={selectedParallax && selectedParallax.id === parallaxData.id}
                    onClick={() => {
                        setSelectedParallax(parallaxData);
                        onSelectParallax(parallaxData);
                        console.log('Parallax selected', parallaxData);
                    }}
                />
            ))}
        </div>
    );
}

export default ParallaxEntityList;
