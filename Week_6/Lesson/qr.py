import qrcode
import os

link = "https://github.com/dylanj1383"
img = qrcode.make(link)

script_dir = os.path.dirname(__file__)
img.save(os.path.join(script_dir, "qr.png"))
