import React from 'react';
import { Button, ButtonGroup, Icon } from '@blueprintjs/core';
import './Sidebar.css';

function Sidebar({ isOpen, onClose, isAnimating, toggleAnimation, onResetAnimation }) {
    const Close = () => {
        onClose();
    }

    const handleAnimationClick = () => {
        toggleAnimation();
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
                <div className="sidebar-controls">
                    <ButtonGroup minimal={true}>
                        <Button icon={<Icon icon={isAnimating ? "pause" : "play"} />} onClick={handleAnimationClick} />
                    </ButtonGroup>
                </div>
            </div>
        </div>
    );
}

export default Sidebar;
