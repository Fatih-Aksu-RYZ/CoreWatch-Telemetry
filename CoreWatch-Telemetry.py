import serial,time,psutil,subprocess
SERIAL_PORT='COM3'
BAUD_RATE=115200
try:
    ser=serial.Serial(SERIAL_PORT,BAUD_RATE,timeout=1)
except:
    exit()
def get_gpu_data():
    try:
        cmd="nvidia-smi --query-gpu=temperature.gpu,utilization.gpu,power.draw --format=csv,noheader,nounits"
        parts=subprocess.check_output(cmd,shell=True).decode('utf-8').strip().split(',')
        t,u,w=int(float(parts[0].strip())),int(float(parts[1].strip())),int(float(parts[2].strip()))
        return t,u,(0 if w>250 else w)
    except:
        return 0,0,0
while True:
    try:
        gt,gu,gw=get_gpu_data()
        cu=int(psutil.cpu_percent())
        ram=int(psutil.virtual_memory().percent)
        b=psutil.sensors_battery()
        bat=int(b.percent) if b else 100
        ser.write(f"{gt},{gu},{gw},{cu},{ram},{bat}\n".encode('ascii'))
    except serial.SerialException:
        break
    except KeyboardInterrupt:
        break
    except:
        pass
    time.sleep(1)