import json
import random

def generate_mob(current_tick):
    mob_types = ["cancerMob", "pataPataMob"]
    mob_type = random.choice(mob_types)
    position_y = random.randint(0, 950)
    drop_powerup = random.choices([True, False], weights=[10, 90], k=1)[0]

    return {
        "tick": current_tick,
        "mobType": mob_type,
        "position": {
            "x": 2000,
            "y": position_y
        },
        "dropPowerup": drop_powerup
    }

def main():
    mobs = []
    current_tick = 0

    for _ in range(299):
        tick_interval = random.randint(5, 100)
        current_tick += tick_interval
        mob = generate_mob(current_tick)
        mobs.append(mob)

    # Ajout du mob de type boss à la fin
    current_tick += random.randint(200, 500)
    mobs.append({
        "tick": current_tick,
        "mobType": "boss",
        "position": {
            "x": 2000,
            "y": 475
        },
        "dropPowerup": False
    })

    with open("map1.json", "w") as outfile:
        json.dump({"mobs": mobs}, outfile, indent=4)

if __name__ == "__main__":
    main()
