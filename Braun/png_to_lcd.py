from PIL import Image

img = Image.open("pics\\main.jpg").convert("RGB")
img = img.resize((80, 60))

width, height = img.size

with open("include/main_tv.h", "w") as f:
    f.write("#pragma once\n")
    f.write("#include <avr/pgmspace.h>\n")
    f.write(f"const uint16_t image[{width * height}] PROGMEM = {{\n")
    
    count = 0
    total = width * height
    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            rgb565 = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
            f.write(f"0x{rgb565:04X}")
            count += 1
            if count < total:
                f.write(", ")
            if count % 16 == 0:
                f.write("\n")
    
    f.write("\n};\n")

print(f"Done! Generated {width}x{height} = {total} pixels")