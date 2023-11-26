# Compiler avec cmake
La compilation s'effectue depuis le répertoire de build (`cd build/`)

Générer le Makefile
`cmake ..`

Générer le Makefile avec les symboles de débogage
`cmake -DCMAKE_BUILD_TYPE=Debug ..`

Compiler avec le Makefile créé
`make`
