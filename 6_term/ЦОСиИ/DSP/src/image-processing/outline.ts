import { getPixelRGB, hexToRGB, colorInRange, getDistinctColors } from "./utils";

function isColorShouldBeChanged(color1, color2) {
    if(colorInRange(color1, color2)) {
        return false;
    }

    return true;
}

const changePixel = (pixel, colors) => {
    let count = 0;

    for(let i = 0; i < colors.length; i++) {
        if(isColorShouldBeChanged(pixel, colors[i])) {
            count++;
        }
    }

    if(count == colors.length) {
        return {...pixel, alpha: 0};
    }

    return pixel;
}

const handleOnload = (img) => {
    const canvas = document.getElementById("canvas") as HTMLCanvasElement;
    const context = canvas.getContext("2d");

    canvas.width = img.width;
    canvas.height = img.height;

    context.drawImage(img, 0, 0);

    const imageData = context.getImageData(0, 0, img.width, img.height);
    let output = new Uint8ClampedArray(imageData.data.length);

    const width = imageData.width;
    const height = imageData.height;

    const badColors = [
        {red: 135, green: 113, blue: 100},
        {red: 185, green: 185, blue: 185}, 
        {red: 194, green: 192, blue: 194}
    ]

    const cols = getDistinctColors(imageData, 7, 180).filter(color => {
        return !badColors.some(colorInRange.bind(null, color));
    });

    
    for (let i = 0; i < imageData.data.length; i += 4) {
        const pixel = getPixelRGB(imageData.data, i);
        let newPixel = changePixel(pixel, cols);

        output[i] = newPixel.red;
        output[i + 1] = newPixel.green;
        output[i + 2] = newPixel.blue;
        output[i + 3] = newPixel.alpha;
    }   

    const newImage = new ImageData(output, width, height);

    context.putImageData(newImage, 0, 0);
}

document.getElementById('fileInput').addEventListener('change', function(event) {
    const file = (event.target as HTMLInputElement).files[0];
    if (!file) return;

    const reader = new FileReader();

    reader.onload = function(e) {
        const img = new Image();
        img.onload = () => {
            handleOnload(img)
        };

        img.src = e.target.result as string;
    };
    reader.readAsDataURL(file);
});