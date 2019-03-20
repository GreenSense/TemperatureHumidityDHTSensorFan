# python
if ! type "python" > /dev/null; then
  sudo apt-get -qq install -y python python-pip
fi

# platform.io
if ! type "pio" > /dev/null; then
  python -c "$(curl -fsSL https://raw.githubusercontent.com/platformio/platformio/develop/scripts/get-platformio.py)"
fi

platformio upgrade
