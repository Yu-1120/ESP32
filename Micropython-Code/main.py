import machine

# 设定GPIO引脚
pin = machine.Pin(2, machine.Pin.OUT)
pin.value(1)  # 亮