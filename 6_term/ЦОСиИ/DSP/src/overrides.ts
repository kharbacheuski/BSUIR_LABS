
type Axis = {
	coords: {
		x: number,
		y: number
	}[],
	x: number[],
	y: number[]
}

export const getAxis = (func: (arg: number) => number, N: number): Axis => {
	const axis = [];

	for (let i = 1; i <= N; i++) {
		let arg = 2*Math.PI*i/N;

		axis.push({
			x: Number(arg.toFixed(2)),
			y: Number(func(arg).toFixed(3))
		})
    }

	const x = axis.map(point => point.x);
	const y = axis.map(point => point.y)
	
	return {
		coords: axis,
		x,
		y 
	}
}

export const getPoints = (N: number): number[] => {
	const points: number[] = [];
	
	for(var i = 0; i < N; i++) {
		points.push(i);
	}

	return points;
}