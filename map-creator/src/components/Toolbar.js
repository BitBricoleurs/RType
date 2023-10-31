// src/components/Toolbar.js
import React, { useState } from 'react';
import { Tabs, Tab } from '@blueprintjs/core';
import '@blueprintjs/core/lib/css/blueprint.css';
import './Toolbar.css';
import EntityList from './EntityList';
import Sidebar from './Sidebar';

function Toolbar({ setSelectedCard, selectedCard }) {
    const [selectedTabId, setSelectedTabId] = useState('entity');
    const [isSidebarOpen, setSidebarOpen] = useState(false);

    const handleTabChange = (newTabId) => {
        setSelectedTabId(newTabId);
    };

    const handleSidebarToggle = () => {
        setSidebarOpen(prevState => !prevState);
    };

    return (
        <div className="toolbar">
            <Tabs id="Tabs" selectedTabId={selectedTabId} onChange={handleTabChange}>
                <Tab id="entity" title="Entité" panel={<EntityList setSelectedCard={setSelectedCard} selectedCard={selectedCard} />} />
                <Tab id="parallax" title="Parallax" panel={<EntityList setSelectedCard={setSelectedCard} selectedCard={selectedCard} />} />
                <Tabs.Expander />
            </Tabs>
            <Sidebar isOpen={isSidebarOpen} onClose={handleSidebarToggle} />
        </div>
    );
}

export default Toolbar;
