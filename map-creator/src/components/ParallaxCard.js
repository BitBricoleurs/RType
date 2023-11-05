// src/components/ParallaxCard.js
import React from 'react';
import './Card.css';

function ParallaxCard({ src, name, isSelected, onClick }) {
    return (
        <div className={`card ${isSelected ? 'selected' : ''}`} onClick={onClick}>
            <img src={process.env.PUBLIC_URL + src} alt={name} />
            <div className="card-text">{name}</div>
        </div>
    );
}

export default ParallaxCard;
