import sys
import time
import random

# Liste des traders légitimes
legit_traders = ["Goldman", "JP_Morgan", "Morgan_Stanley", "Retail_Bob"]
# Le méchant
attacker = "HFT_Predator"

print("--- Démarrage de la simulation de marché ---", file=sys.stderr)
time.sleep(2) # On laisse le temps au C++ de démarrer

# Phase 1 : Trafic Normal (Tout le monde trade gentiment)
for i in range(50):
    trader = random.choice(legit_traders)
    price = round(random.uniform(100, 200), 2)
    qty = random.randint(1, 100)
    # Format CSV : TRADER,SIDE,PRICE,QTY
    print(f"{trader},BUY,{price},{qty}", flush=True)
    time.sleep(0.01) # 100 ordres par seconde (normal)

# Phase 2 : L'ATTAQUE (Quote Stuffing)
# L'attaquant envoie 1000 ordres instantanément sans délai
print("--- ⚠️ LANCEMENT DE L'ATTAQUE QUOTE STUFFING ---", file=sys.stderr)
for i in range(500):
    price = round(random.uniform(100, 200), 2)
    print(f"{attacker},SELL,{price},10", flush=True)

# Phase 3 : Retour au calme (pour voir si l'attaquant est bien banni mais pas les autres)
time.sleep(1)
print("--- Retour au trafic normal ---", file=sys.stderr)
for i in range(50):
    trader = random.choice(legit_traders)
    print(f"{trader},BUY,150.00,10", flush=True)
    # On essaie de faire passer l'attaquant encore une fois
    print(f"{attacker},BUY,150.00,10", flush=True)
    time.sleep(0.01)