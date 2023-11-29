Bonjour à tous et à toutes,

Nous sommes fiers de vous présenter notre projet R-type, réalisé par notre groupe composé de Clément Lagasse, Harry Viennot, Théophilus Homawoo, Bartosz Michalak et Alexandre Lagasse. Nous tenons à exprimer notre gratitude envers nos encadrants pour nous avoir offert la chance de nous présenter au niveau national et de potentiellement obtenir un financement.

Notre projet se distingue par les points forts suivants :

- Game Engine: Nous avons créé un moteur de jeu doté d'une architecture ECS modulaire, ce qui lui permet de prendre en charge n'importe quel type de jeu et d'implémenter divers systèmes. Notre moteur englobe le moteur de rendu, le moteur physique, ainsi que le moteur audio (avec une prise en charge du son en 3D). Nous avons mis en place un système de plugins pour l'ECS et des bibliothèques pour les différents moteurs mentionnés précédemment.

- Game Design: Notre objectif était de rester fidèles au jeu R-type original en utilisant les ressources graphiques des monstres et des vaisseaux, tout en ajoutant notre touche personnelle grâce à des parallaxes et des éléments de décor uniques. Nous avons également inclus une variété d'ennemis, y compris un boss inspiré du jeu original.

- RFC et librairie réseau: Nous avons élaboré une RFC (Request for Comments) exhaustive qui permet à d'autres développeurs d'utiliser notre protocole pour créer des serveurs et des clients capables de communiquer avec notre système. En outre, nous avons créé une bibliothèque réseau réutilisable pour d'autres projets.

- Console de débogage: Pour faciliter le développement, nous avons mis en place une console de débogage qui peut être exécutée en externe (sur un autre terminal) lorsque le serveur est actif. Elle offre un point de connexion permettant d'interagir avec le serveur.

- Cinématiques: Nous avons intégré la possibilité de créer des cinématiques en définissant les mouvements des objets dans la scène, tout en permettant le déplacement de la caméra et le zoom.

- Créateur/Éditeur de cartes: Notre outil de création de cartes permet de générer des niveaux en quelques secondes. Il permet de placer facilement des monstres et des éléments de parallaxe tout en visualisant le rendu en temps réel. Les paramètres de vitesse des éléments peuvent être ajustés dans les fichiers de configuration. De plus, nous avons implémenté des fonctions de sauvegarde et de chargement pour les cartes déjà générées.

Configuration flexible: Pour garantir une grande flexibilité, nous avons adopté une approche basée sur des fichiers JSON entièrement configurables. Ainsi, notre code ne comporte aucune variable en dur, ce qui facilite la gestion de tous les éléments à l'aide de fichiers de configuration dédiés.

Nous espérons que ce résumé met en lumière les points forts de notre projet R-type. N'hésitez pas à nous poser des questions ou à en savoir plus sur nos réalisations. Merci pour votre attention.