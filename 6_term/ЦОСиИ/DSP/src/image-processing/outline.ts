import { getPixelRGB } from "./utils";

export function isPixelIsBright(pixel, accurace = 0.6) {
    const avg = (pixel.red + pixel.green + pixel.blue) / 3;
    if(avg == 0)
        return false

    if(Math.abs((avg - pixel.red) / avg) > accurace 
    || Math.abs((avg - pixel.green) / avg) > accurace 
    || Math.abs((avg - pixel.blue) / avg) > accurace
    ) {
        return true
    }

    return false
}

export function removeBackground(img, context) {
    context.drawImage(img, 0, 0);

    const imageData = context.getImageData(0, 0, img.width, img.height);
    let output = new Uint8ClampedArray(imageData.data.length);

    const width = imageData.width;
    const height = imageData.height;

    for (let i = 0; i < imageData.data.length; i += 4) {
        const pixel = getPixelRGB(imageData.data, i);
        let newPixel = {...pixel};

        if(!isPixelIsBright(pixel)) {
            newPixel = {...pixel, alpha: 0};
        }

        output[i] = newPixel.red;
        output[i + 1] = newPixel.green;
        output[i + 2] = newPixel.blue;
        output[i + 3] = newPixel.alpha;
    }   

    const newImage = new ImageData(output, width, height);

    return newImage
}

document.getElementById('fileInput').addEventListener('change', function(event) {
    const file = (event.target as HTMLInputElement).files[0];
    if (!file) return;

    const reader = new FileReader();

    reader.onload = function(e) {
        const img = new Image();
        img.onload = () => {
            const canvas = document.getElementById("canvas") as HTMLCanvasElement;
            const context = canvas.getContext("2d");

            canvas.width = img.width;
            canvas.height = img.height;

            const newImage = removeBackground(img, context);
            
            context.putImageData(newImage, 0, 0);
        };

        img.src = e.target.result as string;
    };
    reader.readAsDataURL(file);
});