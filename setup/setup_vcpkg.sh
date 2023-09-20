VCPKG_DIR="./vcpkg"

LIBRARIES=(
  "sdl2-net"
)

for LIB in "${LIBRARIES[@]}"; do
  $VCPKG_DIR/vcpkg install $LIB
done

echo "Installation terminée !"
