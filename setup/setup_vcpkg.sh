LIBRARIES=(
  "sdl2-net"
)

for LIB in "${LIBRARIES[@]}"; do
  ./vcpkg/vcpkg install $LIB
done

echo "Installation terminée !"
