tell application "Finder"
    delay 2
    set dmg_window to the front Finder window
    set dmg_bounds to bounds of dmg_window

    set icon_size to 100
    set sidebar_width to 120

    tell dmg_window
        set current view to icon view
        set the icon size of the icon view options to icon_size
        set the arrangement of the icon view options to not arranged
        set the bounds to {dmg_bounds's item 1, dmg_bounds's item 2, dmg_bounds's item 1 + (2 * sidebar_width) + (2 * icon_size), dmg_bounds's item 2 + (2 * sidebar_width) + (2 * icon_size)}
    end tell

    set position of item "MonApplication" of dmg_window to {icon_size, icon_size}
    set position of item "Applications" of dmg_window to {icon_size * 2 + sidebar_width, icon_size}

    close dmg_window
end tell
