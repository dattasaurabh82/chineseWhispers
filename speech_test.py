#!/usr/bin/env python3

# NOTE: this example requires PyAudio because it uses the Microphone class

import speech_recognition as sr
import json
import StringIO as io

credentials_json_file = 'Leo-Dolls-cdab5e3e2bbf.json'

# recognize speech using Google Cloud Speech
GOOGLE_CLOUD_SPEECH_CREDENTIALS = r"""
"""

with open(credentials_json_file) as json_file:
	json_data = json.load(json_file)
	GOOGLE_CLOUD_SPEECH_CREDENTIALS = json.dumps(json_data).decode("utf-8")

# GOOGLE_CLOUD_SPEECH_CREDENTIALS = open(credentials_json_file)

print GOOGLE_CLOUD_SPEECH_CREDENTIALS

# obtain audio from the microphone
r = sr.Recognizer()
with sr.Microphone() as source:
    print("Say something!")
    audio = r.listen(source)

try:
    print("Google Cloud Speech thinks you said " + r.recognize_google_cloud(audio, credentials_json=GOOGLE_CLOUD_SPEECH_CREDENTIALS))
except sr.UnknownValueError:
    print("Google Cloud Speech could not understand audio")
except sr.RequestError as e:
    print("Could not request results from Google Cloud Speech service; {0}".format(e))
