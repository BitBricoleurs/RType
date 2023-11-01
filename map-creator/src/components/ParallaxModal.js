import React, { useState } from 'react';
import { Dialog, FormGroup, NumericInput, Switch, Button, DialogBody, DialogFooter } from '@blueprintjs/core';
import '@blueprintjs/core/lib/css/blueprint.css';
import './ParallaxModal.css';

function ParallaxModal({ parallaxData, onClose, setSelectedParallax, placeParallaxEntities, onDeleteParallax }) {
    const [layer, setLayer] = useState(parallaxData.layer);
    const [speed, setSpeed] = useState(parallaxData.speed);
    const [isLooping, setIsLooping] = useState(parallaxData.isLooping);
    const [isBackgroundEnabled, setIsBackgroundEnabled] = useState(parallaxData.isBackgroundEnabled);

    const handleSave = () => {
        const updatedParallax = {
            ...parallaxData,
            layer: layer,
            speed: speed,
            isLooping: isLooping,
            isBackgroundEnabled: isBackgroundEnabled
        };

        setSelectedParallax(updatedParallax); // Mise à jour du parallax courant
        placeParallaxEntities(updatedParallax); // Placement des entités parallax sur la map
        onClose();
    };

    const handleDelete = () => {
        onDeleteParallax(parallaxData); // Appelle la fonction de suppression passée en props
        onClose();
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
                <FormGroup label="Speed" labelFor="speed-input">
                    <NumericInput id="speed-input" value={speed} onValueChange={setSpeed} min={0} />
                </FormGroup>
                <FormGroup label="Is Looping" labelFor="is-looping-switch">
                    <Switch id="is-looping-switch" checked={isLooping} onChange={() => setIsLooping(!isLooping)} />
                </FormGroup>
                <FormGroup label="Background" labelFor="is-background-switch">
                    <Switch
                        id="is-background-switch"
                        checked={isBackgroundEnabled}
                        onChange={() => setIsBackgroundEnabled(!isBackgroundEnabled)}
                    />
                </FormGroup>
            </DialogBody>
            <DialogFooter actions={
                <div>
                    <Button text="Annuler" onClick={onClose} />
                    <Button intent="danger" text="Supprimer" onClick={handleDelete} />
                    <Button intent="primary" text="Sauvegarder" onClick={handleSave} />
                </div>
            }>
            </DialogFooter>
        </Dialog>
    );
}

export default ParallaxModal;
