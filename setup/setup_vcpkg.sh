LIBRARIES=(
  "sdl2-net"
  "raylib"
)

for LIB in "${LIBRARIES[@]}"; do
  ./vcpkg/vcpkg install $LIB
done

echo "Installation terminée !"
