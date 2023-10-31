// src/components/LayerManager.js
import React, { useState } from 'react';

function LayerManager() {
    const [layers, setLayers] = useState([
        { name: 'Layer 1', visible: true },
        { name: 'Layer 2', visible: true },
        // ... autres calques initiaux
    ]);

    const toggleLayerVisibility = index => {
        const newLayers = layers.slice();
        newLayers[index].visible = !newLayers[index].visible;
        setLayers(newLayers);
    };

    return (
        <div className="layer-manager">
            {layers.map((layer, index) => (
                <div key={index} className="layer">
                    <button onClick={() => toggleLayerVisibility(index)}>
                        {layer.visible ? 'Hide' : 'Show'}
                    </button>
                    {layer.name}
                </div>
            ))}
        </div>
    );
}

export default LayerManager;
