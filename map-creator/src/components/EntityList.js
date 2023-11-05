// src/components/EntityList.js
import './EntityList.css';
import Card from './Card';
import data from '../data.json';

function EntityList({ setSelectedCard, selectedCard }) {
    return (
        <div className="entity-list">
            {data.map((cardData, index) => (
                <Card
                    key={index}
                    src={cardData.src}
                    name={cardData.name}
                    isSelected={selectedCard === cardData}
                    onClick={() => setSelectedCard(cardData)}
                />
            ))}
        </div>
    );
}
export default EntityList;
