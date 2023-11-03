import React, { useState } from 'react';
import { Dialog, FormGroup, NumericInput, Switch, Button, DialogBody, DialogFooter } from '@blueprintjs/core';
import '@blueprintjs/core/lib/css/blueprint.css';
import './ParallaxModal.css';

function ParallaxModal({ parallaxData, onClose, setSelectedParallax, placeParallaxEntities, onDeleteParallax }) {
    const [layer, setLayer] = useState(parallaxData.layer);
    const [isLooping, setIsLooping] = useState(parallaxData.isLooping);
    const [isBackgroundEnabled, setIsBackgroundEnabled] = useState(parallaxData.isBackgroundEnabled);

    const handleSave = () => {
        const updatedParallax = {
            ...parallaxData,
            layer: layer,
            isLooping: isLooping,
            isBackgroundEnabled: isBackgroundEnabled
        };

        setSelectedParallax(updatedParallax);
        placeParallaxEntities(updatedParallax);
        onClose();
    };

    const handleDelete = () => {
        onDeleteParallax(parallaxData);
        onClose();
    };

    const handleBackgroundChange = () => {
        const newIsBackgroundEnabled = !isBackgroundEnabled;
        setIsBackgroundEnabled(newIsBackgroundEnabled);
        if (newIsBackgroundEnabled) {
            setIsLooping(true);
        }
    };

    const handleLoopingChange = () => {
        const newIsLooping = !isLooping;
        setIsLooping(newIsLooping);
        if (!newIsLooping && isBackgroundEnabled) {
            setIsBackgroundEnabled(false);
        }
    };


    return (
        <Dialog
            isOpen={true}
            onClose={onClose}
            title="Modifier l'élément Parallax"
            className="parallax-modal"
        >
            <DialogBody>
                <FormGroup label="Layer" labelFor="layer-input">
                    <NumericInput id="layer-input" value={layer} onValueChange={setLayer} min={0} />
                </FormGroup>
                <FormGroup label="Is Looping" labelFor="is-looping-switch">
                    <Switch id="is-looping-switch" checked={isLooping} onChange={handleLoopingChange} />
                </FormGroup>
                <FormGroup label="Background" labelFor="is-background-switch">
                    <Switch
                        id="is-background-switch"
                        checked={isBackgroundEnabled}
                        onChange={handleBackgroundChange}
                    />
                </FormGroup>
            </DialogBody>
            <DialogFooter>
                <div className="button-group">
                    <Button text="Annuler" onClick={onClose} className="button-spacing cancel-button" />
                    <Button intent="danger" text="Supprimer" onClick={handleDelete} className="button-spacing" />
                    <Button intent="primary" text="Sauvegarder" onClick={handleSave} className="button-spacing" />
                </div>
            </DialogFooter>
        </Dialog>
    );
}

export default ParallaxModal;
