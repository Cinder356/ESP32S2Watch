const sharp = require('sharp');
const fs = require('fs');
const path = require('path');

const input_image_path = '../../images/minesweeper_bomb.png';
const output_image_path = '../../bin-images/' + path.parse(input_image_path).name + '.bin';
// const output_path = ; 

// Функция для преобразования RGB в RGB565
function rgbToRgb565(r, g, b) {
    const r5 = (r >> 3) & 0x1F;
    const g6 = (g >> 2) & 0x3F;
    const b5 = (b >> 3) & 0x1F;
    return (r5 << 11) | (g6 << 5) | b5;
}

// Загрузка изображения и преобразование его в массив RGB565
sharp(input_image_path)
    .raw()
    .ensureAlpha()
    .toBuffer((err, data, info) => {
        if (err) {
            console.error('Error:', err);
            return;
        }

        const width = info.width;
        const height = info.height;
        const rgb565Array = new Uint16Array(width * height);

        for (let i = 0; i < width * height; i++) {
            const r = data[i * 4];
            const g = data[i * 4 + 1];
            const b = data[i * 4 + 2];
            // const a = data[i * 4 + 3]; // Альфа-канал (не используется в RGB565)

            rgb565Array[i] = rgbToRgb565(r, g, b);
        }
        console.log(rgb565Array);

        // Сохранение массива RGB565 в бинарный файл
        // const buffer = Buffer.from(rgb565Array.buffer);
        // fs.writeFile(output_image_path, buffer, (err) => {
        //     if (err) {
        //         console.error('Error writing file:', err);
        //     } else {
        //         console.log('File saved successfully.');
        //     }
        // });
    });
