import { getPixelRGB } from "./utils";

function isColorShouldBeChanged(color1, color2) {
    const accurace = 24;

    const inRange = (color, basis) => {
        return color >= basis - accurace && color <= basis + accurace
    };

    if(inRange(color1.red, color2.red) && inRange(color1.green, color2.green) && inRange(color1.blue, color2.blue)) {
        return false;
    }

    return true;
}

const changePixel = (pixel) => {
    const color = [
        {
            red: 18,
            green: 70,
            blue: 130
        },
        {
            red: 56,
            green: 134,
            blue: 14
        },
        {
            red: 9,
            green: 143,
            blue: 255
        }
    ]

    let count = 0;

    for(let i = 0; i < color.length; i++) {
        if(isColorShouldBeChanged(pixel, color[i])) {
            count++;
        }
    }

    if(count == color.length) {
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

    // const matrix = convertTo2DArray(imageData.data, width);
                    
    for (let i = 0; i < imageData.data.length; i += 4) {
        const pixel = getPixelRGB(imageData.data, i);
        let newPixel = changePixel(pixel);

        output[i] = newPixel.red;
        output[i + 1] = newPixel.green;
        output[i + 2] = newPixel.blue;
        output[i + 3] = newPixel.alpha;
    }   

    // output = new Uint8ClampedArray(convertTo1DArray(output));

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