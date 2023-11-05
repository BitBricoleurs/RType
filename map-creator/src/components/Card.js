import React from 'react';
import './Card.css';

function Card({ src, name, isSelected, onClick }) {
    return (
        <div className={`card ${isSelected ? 'selected' : ''}`} onClick={onClick}>
            <img src={process.env.PUBLIC_URL + src} alt={name} />
            <div className="card-text">{name}</div>
        </div>
    );
}

export default Card;
