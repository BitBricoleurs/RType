// src/components/Sidebar.js
import React from 'react';
import { Button } from '@blueprintjs/core';
import './Sidebar.css';

function Sidebar({ isOpen, onClose }) {

    const Close = () => {
        console.log(onClose);  // Ajoutez cette ligne dans votre fonction Sidebar ou Close

        onClose();
    }


    return (
        <div className={`sidebar ${isOpen ? 'open' : 'closed'}`}>
            <Button
                icon="menu"
                className="sidebar-toggle-button"
                onClick={Close}

            />
            <div className="sidebar-content">
                <h1>Map Creator</h1>
            </div>
        </div>
    );
}

export default Sidebar;
