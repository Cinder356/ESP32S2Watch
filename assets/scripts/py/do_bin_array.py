import struct


def rgb888_to_rgb565(rgb888):
    # Извлекаем компоненты цвета из списка
    red = rgb888[0]
    green = rgb888[1]
    blue = rgb888[2]

    # Преобразование значений компонентов в RGB565
    red565 = (red >> 3) & 0x1F
    green565 = (green >> 2) & 0x3F
    blue565 = (blue >> 3) & 0x1F

    # Сборка нового 16-бит  ого значения
    rgb565 = (red565 << 11) | (green565 << 5) | blue565

    return rgb565


def save_list(file_path, arr):
    with open(file_path, "wb") as f:
        for number in arr:
            binary_data = struct.pack("<H", number)  # "<H" - формат для uint16_t
            f.write(binary_data)


def print_bin_array(file_path):
    with open(file_path, 'rb') as file:
        binary_data = file.read()
        uint16_arr = struct.unpack('H' * (len(binary_data) // 2), binary_data)
    print(uint16_arr)


def read_bmp_to_pixel_array(file_path):
    pixel_array = []

    with open(file_path, 'rb') as f:
        # Чтение заголовка BMP (первые 54 байта)
        header = f.read(54)

        # Извлечение ширины и высоты из заголовка BMP
        width = struct.unpack('<I', header[18:22])[0]
        height = struct.unpack('<I', header[22:26])[0]

        # Чтение данных пикселей BMP
        for _ in range(height):
            row = []
            for _ in range(width):
                # Чтение значения пикселя (байты BGR)
                b, g, r = struct.unpack('BBB', f.read(3))
                row.append([r, g, b])  # Преобразование в формат RGB
            pixel_array.append(row)

    return pixel_array


def convert_img(input_path: str, output_path: str, save_to_bin: bool):
    img_list = read_bmp_to_pixel_array(input_path)
    img_list_565 = []
    for row_i in range(len(img_list) - 1, -1, -1):
        for pixel_888 in img_list[row_i]:
            img_list_565.append(rgb888_to_rgb565(pixel_888))
    with open('arr.txt', 'w') as f:
        for i in img_list_565:
            f.write(f"{hex(i)}, ")
    print(img_list_565)
    if save_to_bin:
        save_list(output_path, img_list_565)
        print_bin_array(output_path)


def main():
    name = "h"
    save_to_bin = True

    convert_img(f"../images/{name}.bmp", f"../bin-images/{name}.bin", save_to_bin)


if __name__ == '__main__':
    main()
