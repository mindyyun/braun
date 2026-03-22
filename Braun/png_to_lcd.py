from PIL import Image

img = Image.open("pics\\main_tv.png").convert("RGB")
img = img.resize((80, 60))  # ~9.4KB — safe for Uno

pixels = list(img.getdata())

with open("include/main_tv.h", "w") as f:
    f.write("#pragma once\n")
    f.write("#include <avr/pgmspace.h>\n")
    f.write(f"const uint16_t image[{len(pixels)}] PROGMEM = {{\n")
    for i, (r, g, b) in enumerate(pixels):
        rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
        f.write(f"0x{rgb565:04X}")
        if i < len(pixels) - 1:
            f.write(", ")
        if (i + 1) % 16 == 0:
            f.write("\n")
    f.write("\n};\n")