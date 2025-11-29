# Image de base C++ (GCC)
FROM gcc:latest

WORKDIR /app

# On installe Python (pour l'attaquant)
RUN apt-get update && apt-get install -y python3

# Copie des fichiers
COPY engine.cpp .
COPY attacker.py .

# 1. Compilation du code C++ (Optimisation -O3 pour la vitesse max)
RUN g++ -O3 -o market_engine engine.cpp

# 2. Commande de lancement : 
# Python génère les ordres -> Pipe (|) -> Le moteur C++ les traite
CMD ["sh", "-c", "python3 attacker.py | ./market_engine"]