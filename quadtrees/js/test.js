const quadtree = require('./quadtree');
const Q = quadtree();
let i = 0;
for (; i < 10000; i++) {
    Q.add_point([
        Number((Math.random() * (180 - -180) + -180).toFixed(3)),
        Number((Math.random() * (90 - -90) + -90).toFixed(3))
    ])
}

for (i = 0; i < 500; i++) {
    Q.query([
        Number((Math.random() * (180 - -180) + -180).toFixed(3)),
        Number((Math.random() * (90 - -90) + -90).toFixed(3)),
        Number((Math.random() * (180 - -180) + -180).toFixed(3)),
        Number((Math.random() * (90 - -90) + -90).toFixed(3))
    ])
}

