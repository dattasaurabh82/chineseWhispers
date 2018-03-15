import speech_recognition as sr
import serial
import serial.tools.list_ports
import time
import io
import os

# FOLDER STRUCTURE VERIFICATION
audio_file_directory = "recorded_files"
if not os.path.exists(audio_file_directory):
    os.makedirs(recorded_files)
# else:
#     print "folder exists"

time.sleep(1)

# AUTOMATICALLY FIND AND ASIGN ARDUINO SERIAL PORT
arduino_serial_port = ''

ports_list = list(serial.tools.list_ports.comports())
for port in ports_list:
    # print port
    # if "ttyACM" in port[1]:  #for pi
    if "Arduino" in port[1] or "ttyACM" in port[1]: 
        arduino_serial_port = port[0]

print ("Found and Arduino attached to computer: " + str(arduino_serial_port))

proceed = False
transcribed_sentence = ""

ser = serial.Serial()
ser.baudrate = 9600
ser.port = arduino_serial_port
# print type(ser.port)
# print ser.port
ser.timeout = 4 

time.sleep(2)

# ESTABLISH SERIAL CONNECTION

try:
    print "Trying to connect to that serial port"
    time.sleep(2)
    ser.open()
    proceed = True
except:
    print "For some error, could'nt connect to the above serial port"
    pass 
finally:
    proceed = True
    if proceed:
        print("Serial port opened at: " + str(ser.name) + ", with baudrate: " + str(ser.baudrate)) 


# CHECK FOR SERIAL TRIGGER TO START LISTENING AND ALL THE BULLSHIT ROUTINES FOLLOWING THAT
lame_msg_c = 0
file_counter = 0

serial_trig_val = 6

def main():
    try:
        while True:
            if proceed: # EXTRA CHECK

                # Read the serial data
                incoming_trig = ser.readline().rstrip() #.rstrip() removes any /r/n
                if not incoming_trig:
                    lame_msg_c += 1
                    if(lame_msg_c == 1):
                        print "\nWaiting for Serial trigger..."
                    continue

                # print incoming_trig
                
                # If it receives a signal from Arduino the proceed
                global serial_trig_val
                if int(incoming_trig) == serial_trig_val:
                    print "Received trigger and thus starting listener.."

                    time.sleep(2)

                    # Obtain audio from the microphone
                    r = sr.Recognizer()
                    with sr.Microphone() as source:
                        print("\n\nListening...")
                        audio = r.listen(source)

                    time.sleep(2)

                    # write audio to a WAV file
                    print("Saving audio file...") 
                    global file_counter
                    with open(audio_file_directory+"/"+str(file_counter)+".wav", "wb") as f:
                        f.write(audio.get_wav_data())
                    print("Saved :)")
                    file_counter += 1

                    # --------- Recognize speech using Google Speech Recognition
                    # time.sleep(2)
                    # try:
                    #     # For testing purposes, we're just using the default API key
                    #     # to use another API key, use `r.recognize_google(audio, key="GOOGLE_SPEECH_RECOGNITION_API_KEY")`
                    #     # instead of `r.recognize_google(audio)`
                    #     print("Recognizing...")
                    #     #transcribed_sentence = r.recognize_google(audio, "zh-CN")
                    #     transcribed_sentence = r.recognize_google(audio, "en-US")
                    #     print("Recognized :)")
                    #     time.sleep(2)
                    #     print("\nIt heard: -->\"" + transcribed_sentence + "\"")

                    #     lame_msg_c = 0

                    # except sr.UnknownValueError:
                    #     print("** Could not understand audio at all")
                    #     exit()
                    # except sr.RequestError as e:
                    #     print("** Could not request results from Google Speech Recognition service; {0}".format(e))
                    #     exit()


                    # --------- Recognize speech using Sphinx
                    try:
                        time.sleep(2)
                        print("Recognizing...")
                        # transcribed_sentence = r.recognize_sphinx(audio, "zh-CN")
                        transcribed_sentence = r.recognize_sphinx(audio, "en-US")
                        print("Recognized :)")
                        time.sleep(2)
                        print("\nIt heard: -->\"" + transcribed_sentence + "\"")

                        lame_msg_c = 0

                    except sr.UnknownValueError:
                        print("** Could not understand audio")
                        exit()
                    except sr.RequestError as e:
                        print("** Sphinx error; {0}".format(e))
                        exit()
                else:
                    print("** Serial trigger didn't match the reqd. trig. " + "6")
                    exit()
            else:
                print ("** Serial port was not opened")
                exit()
    except (KeyboardInterrupt, EOFError):
        ser.close()
        exit()   


if __name__ == '__main__':
    main()  