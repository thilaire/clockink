from PIL import Image, ImageFont, ImageDraw
for l in range(32,256,2):
	font = ImageFont.truetype("digital-7 (mono).ttf",l)
	print("l=", l, "   size=",font.getsize("0"))

# size=52 for 24x38
# size=70 for 32x52
# size=158 for 72x116

font = ImageFont.truetype("digital-7 (mono).ttf",158)
print("l=", l, "   size=",font.getsize("0"))

name = {'.':'point', ':': 'colon', '-': 'minus', '+': 'plus'}

for c in '0123456789:':
	print("Process: '%s'" % c)
	img=Image.new("1",font.getsize("0"), 1)
	draw=ImageDraw.Draw(img)
	draw.text((0,-2), c, font=font, fill="#000000")
	img.save(name.get(c,c) + ".png")