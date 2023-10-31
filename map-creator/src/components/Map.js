// src/components/Map.js
import React, { useState, useCallback } from 'react';
import { MenuItem, Menu } from '@blueprintjs/core';
import './Map.css';

function Map({ onMapClick, mapItems, onDeleteItem }) {
    const [contextMenuState, setContextMenuState] = useState({ isOpen: false, x: 0, y: 0, item: null });

    const handleContextMenu = useCallback((event, item) => {
        event.preventDefault();
        setContextMenuState({ isOpen: true, x: event.clientX, y: event.clientY, item });
    }, []);

    const handleCloseContextMenu = useCallback(() => {
        setContextMenuState({ isOpen: false, x: 0, y: 0, item: null });
    }, []);

    const handleMenuItemClick = useCallback((event, action) => {
        event.stopPropagation();  // Stop event propagation
        if (action === 'Modifier') {
            console.log('Modifier', contextMenuState.item);
        } else if (action === 'Supprimer') {
            onDeleteItem(contextMenuState.item);
        }
        handleCloseContextMenu();
    }, [contextMenuState.item, handleCloseContextMenu, onDeleteItem]);

    return (
        <div className="map" onClick={onMapClick}>
            {mapItems.map((item, index) => (
                <div
                    key={index}
                    style={{
                        position: 'absolute',
                        left: item.x + 'px',
                        top: item.y + 'px',
                        backgroundImage: `url(${process.env.PUBLIC_URL + item.src})`,
                        backgroundSize: 'cover',
                        width: item.rect.width * item.scale + 'px',
                        height: item.rect.height * item.scale + 'px',
                    }}
                    onContextMenu={(event) => handleContextMenu(event, item)}
                />
            ))}
            {contextMenuState.isOpen && (
                <div
                    style={{
                        position: 'fixed',
                        left: contextMenuState.x,
                        top: contextMenuState.y,
                        zIndex: 1000
                    }}
                    onMouseLeave={handleCloseContextMenu}
                >
                    <Menu>
                        <MenuItem text="Modifier" onClick={(event) => handleMenuItemClick(event, 'Modifier')} />
                        <MenuItem text="Supprimer" onClick={(event) => handleMenuItemClick(event, 'Supprimer')} />
                    </Menu>
                </div>
            )}
        </div>
    );
}

export default Map;
