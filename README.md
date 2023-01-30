
### Playing with the INMP441 I2S microphone on the Raspberry Pi Pico

# quick testing:

```
stty -F /dev/ttyACM0 raw
aplay -f S32_LE -c 1 -r 8000 /dev/ttyACM0
```

