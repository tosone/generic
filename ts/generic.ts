interface ITask {
    name: string;

    start?: boolean;

    repeat?: (...args: any[]) => boolean | number; // 这个返回值算是泛型么？

    while?: (...args: any[]) => boolean;

    if?: (...args: any[]) => boolean;
    else?: (...args: any[]) => Promise<any>;

    func?: (...args: any[]) => Promise<any>; // any 算是泛型么？
    // any 在 ts 中不检查任何相关变量类型和相关方法的

    externalFunc?: {
        headers: Map<string, string>;
        method: string;
        url: string;
    };

    requires?: string[];
}

function test<Type extends Array<Number>>(arg: Type): Number {
    return arg.length;
}

console.log(test([1, 2, 3]));

// class GenericNumber<NumType> {
//     zeroValue: NumType;
//     add: (x: NumType, y: NumType) => NumType;
// }

// ts-node ts/generic.ts
