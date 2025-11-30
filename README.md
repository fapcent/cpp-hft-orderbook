# ⚡ C++ High-Frequency Order Book

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=flat&logo=c%2B%2B&logoColor=white) ![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat&logo=linux&logoColor=black) ![Performance](https://img.shields.io/badge/Performance-High-red)

Un moteur de matching (Matching Engine) simplifié conçu pour la **faible latence** et la résilience face aux attaques de marché.

## 🔥 Caractéristiques Techniques

* **Limit Order Book (LOB) :** Gestion efficace d'un carnet d'ordres en mémoire.
* **Anti-DDoS Algorithmique :** Détection en temps réel des stratégies de "Quote Stuffing" (inondation d'ordres).
* **Pipe-based Communication :** Utilisation des flux standards Unix (StdIn/StdOut) pour une intégration système modulaire (Unix Philosophy).

## 🛡️ Sécurité & Robustesse

Le moteur intègre un **Rate Limiter** interne. Si un acteur du marché dépasse un seuil d'ordres par seconde (défini dans \engine.cpp\), il est automatiquement banni du carnet d'ordres sans impacter la latence des autres traders.

## 🚀 Utilisation

Ce projet utilise une architecture **Producer-Consumer** via des pipes Linux :

\\\ash
# Compiler et lancer la simulation (via Docker)
docker build -t lob-guard .
docker run --rm lob-guard
\\\

## 🔬 Pourquoi C++ ?
Dans le HFT, le Garbage Collection (Java/Python) est inacceptable. C++ permet une gestion manuelle de la mémoire et des optimisations processeur (cache locality) indispensables pour atteindre des temps de réponse de l'ordre de la microseconde.
