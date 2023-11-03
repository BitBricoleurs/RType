// src/components/Map.js
import React, { useState, useCallback, useEffect, useRef } from 'react';
import { MenuItem, Menu } from '@blueprintjs/core';
import './Map.css';

function Map({ onMapClick, mapItems, onDeleteItem, backgroundImages, selectedCard, selectedParallax, onParallaxRightClick, OnPowerUp, isAnimating }) {
    const sortedBackgroundImages = backgroundImages.sort((a, b) => b.layer - a.layer);

    const [contextMenuState, setContextMenuState] = useState({ isOpen: false, x: 0, y: 0, item: null });

    const handleContextMenu = useCallback((event, item) => {
        event.preventDefault();
        setContextMenuState({
            isOpen: true,
            x: event.clientX,
            y: event.clientY,
            item
        });
    }, []);

    const handleCloseContextMenu = useCallback(() => {
        setContextMenuState({ isOpen: false, x: 0, y: 0, item: null });
    }, []);

    const handleMenuItemClick = useCallback((event, action) => {
        event.stopPropagation();
        if (action === 'Modifier') {
            console.log('Modifier', contextMenuState.item);
        } else if (action === 'Supprimer') {
            onDeleteItem(contextMenuState.item);
        } else if (action === 'PowerUp') {
            OnPowerUp(contextMenuState.item);
        }
        handleCloseContextMenu();
    }, [contextMenuState.item, handleCloseContextMenu, onDeleteItem, OnPowerUp]);

    const handleMapClickInternal = useCallback((event) => {
        onMapClick(event);
    }, [onMapClick]);

    const handleParallaxContextMenu = useCallback((event, parallaxItem) => {
        event.preventDefault();
        onParallaxRightClick(parallaxItem);
        console.log('Parallax right clicked', parallaxItem);
    }, [onParallaxRightClick]);

    const [backgroundOffsets, setBackgroundOffsets] = useState(backgroundImages.map(() => 0));

    const animationFrameRef = useRef();

    const [itemOffsets, setItemOffsets] = useState(mapItems.map(() => ({ x: 0, y: 0 })));

    const animate = useCallback(() => {
        if (isAnimating) {
            setBackgroundOffsets(currentOffsets =>
                currentOffsets.map((offset, index) => offset + backgroundImages[index].velocity.x)
            );
            mapItems.forEach((item, index) => {
                item.offset = {
                    x: (item.offset?.x || 0) + item.velocity.x,
                    y: (item.offset?.y || 0) + item.velocity.y,
                };
            });
        }
        animationFrameRef.current = requestAnimationFrame(animate);
    }, [isAnimating, backgroundImages, mapItems]);

    useEffect(() => {
        if (isAnimating) {
            animationFrameRef.current = requestAnimationFrame(animate);
        } else {
            cancelAnimationFrame(animationFrameRef.current);
        }
        return () => cancelAnimationFrame(animationFrameRef.current);
    }, [isAnimating, animate]);


    useEffect(() => {
        setItemOffsets(prevItemOffsets => mapItems.map((item, index) =>
            prevItemOffsets.length > index ? prevItemOffsets[index] : { x: 0, y: 0 }
        ));
    }, [mapItems]);

    useEffect(() => {
        setBackgroundOffsets(prevOffsets => backgroundImages.map((image, index) =>
            prevOffsets.length > index ? prevOffsets[index] : 0
        ));
    }, [backgroundImages]);


    return (
        <div className="map" onClick={handleMapClickInternal}>
            {sortedBackgroundImages.map((bg, index) => {
                const xOffset = backgroundOffsets[index] || 0;
                const style = {
                    position: 'absolute',
                    left: `${bg.x + xOffset}px`,
                    top: `${bg.y}px`,
                    backgroundImage: `url(${process.env.PUBLIC_URL + bg.path})`,
                    backgroundSize: 'cover',
                    width: bg.rect.width + 'px',
                    height: bg.rect.height + 'px',
                    zIndex: bg.layer
                };
                return (
                    <div
                        key={`bg-${index}`}
                        style={style}
                        onContextMenu={(event) => handleParallaxContextMenu(event, bg)}
                    />
                );
            })}
            {mapItems.map((item, index) => {

                const itemOffset = item.offset || { x: 0, y: 0 };
                const style = {
                    position: 'absolute',
                    left: `${item.x + itemOffset.x}px`,
                    top: `${item.y + itemOffset.y}px`,
                    backgroundImage: `url(${process.env.PUBLIC_URL + item.src})`,
                    backgroundSize: 'cover',
                    width: item.rect.width * item.scale + 'px',
                    height: item.rect.height * item.scale + 'px',
                    zIndex: 1000,
                    border: item.powerUp ? '3px solid gold' : 'none',
                    boxShadow: item.powerUp ? '0 0 10px gold' : 'none',
                    animation: item.powerUp ? 'pulse 2s infinite' : 'none',
                };
                return (
                    <div
                        key={index}
                        style={style}
                        onContextMenu={(event) => handleContextMenu(event, item)}
                    />
            )})}
            {contextMenuState.isOpen && (
                <div
                    style={{
                        position: 'fixed',
                        left: contextMenuState.x,
                        top: contextMenuState.y,
                        zIndex: 2000
                    }}
                    onMouseLeave={handleCloseContextMenu}
                >
                    <Menu>
                        <MenuItem
                            text="PowerUp"
                            onClick={(event) => handleMenuItemClick(event, 'PowerUp')}
                            icon={contextMenuState.item.powerUp ? "tick" : null}
                        />
                        <MenuItem text="Modifier" onClick={(event) => handleMenuItemClick(event, 'Modifier')} />
                        <MenuItem text="Supprimer" onClick={(event) => handleMenuItemClick(event, 'Supprimer')} />
                    </Menu>
                </div>
            )}
        </div>
    );
}

export default Map;
