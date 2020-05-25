portname="COM$1"
sketch="$2"
arduino --upload --board arduino:avr:mega:cpu=atmega2560 --port ${portname} ${sketch}
