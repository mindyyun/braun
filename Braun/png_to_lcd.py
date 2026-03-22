from PIL import Image

def image_to_arduino(image_path="pics\\tv_bw.jpg", var_name="tv_bw", max_width=80, max_height=80):
    img = Image.open("pics\\tv_bw.jpg")
    
    # Resize to fit within max dimensions while preserving aspect ratio
    img.thumbnail((max_width, max_height), Image.LANCZOS)
    img = img.convert("RGB")
    
    width, height = img.size
    pixels = list(img.getdata())
    
    # Convert RGB888 to RGB565
    def rgb565(r, g, b):
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)
    
    hex_values = [f"0x{rgb565(r,g,b):04X}" for r, g, b in pixels]
    
    # Format into lines of 12 values each
    lines = []
    for i in range(0, len(hex_values), 12):
        lines.append(", ".join(hex_values[i:i+12]))
    
    array_body = ",\n  ".join(lines)
    
    output = f"""// Image: {width}x{height} pixels
const uint16_t {var_name}[] PROGMEM = {{
  {array_body}
}};
#define {var_name.upper()}_WIDTH  {width}
#define {var_name.upper()}_HEIGHT {height}
"""
    
    print(output)
    
    # Also save to a .h file
    with open(f"{var_name}.h", "w") as f:
        f.write(output)
    print(f"Saved to {var_name}.h")
    print(f"Image size: {width}x{height} = {width*height} pixels = {width*height*2} bytes of flash")

image_to_arduino("tv_bw.png", var_name="tv_bw", max_width=320, max_height=460)