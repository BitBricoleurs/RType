// src/components/Toolbar.js
import React, { useState } from 'react';
import { Tabs, Tab } from '@blueprintjs/core';
import '@blueprintjs/core/lib/css/blueprint.css';
import './Toolbar.css';
import EntityList from './EntityList';
import ParallaxEntityList from './ParallaxEntityList';
import Sidebar from './Sidebar';

function Toolbar({ setSelectedCard, selectedCard, setSelectedParallax, selectedParallax, onSelectParallax }) {
    const [selectedTabId, setSelectedTabId] = useState('entity');
    const [isSidebarOpen, setSidebarOpen] = useState(false);

    const handleTabChange = (newTabId) => {
        setSelectedTabId(newTabId);
    };

    const handleSidebarToggle = () => {
        setSidebarOpen(prevState => !prevState);
    };

    const handleSelectEntity = (card) => {
        setSelectedCard(card);
        setSelectedParallax(null);
    };

    const handleSelectParallax = (parallax) => {
        setSelectedParallax(parallax);
        setSelectedCard(null);
        onSelectParallax(parallax);
        console.log('Parallax selected', parallax)
    };

    return (
        <div className="toolbar">
            <Tabs id="Tabs" selectedTabId={selectedTabId} onChange={handleTabChange}>
                <Tab id="entity" title="Entité" panel={<EntityList setSelectedCard={handleSelectEntity} selectedCard={selectedCard} />} />
                <Tab id="parallax" title="Parallax" panel={
                    <ParallaxEntityList setSelectedParallax={handleSelectParallax} selectedParallax={selectedParallax} onSelectParallax={onSelectParallax} />
                } />
                <Tabs.Expander />
            </Tabs>
            <Sidebar isOpen={isSidebarOpen} onClose={handleSidebarToggle} />
        </div>
    );
}


export default Toolbar;
