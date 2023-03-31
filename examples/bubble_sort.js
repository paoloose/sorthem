#!/usr/bin/env node

const arr = [6, 4, 0, 3, 2, 1, 6, 4, 0, 3, 2, 1, 6, 4, 0, 3, 2, 1, 6, 4, 0, 3, 2, 1, 6, 4, 0, 3, 2, 1, 6, 4, 0, 3, 2, 1];

async function sleep(ms) {
  return new Promise((resolve, _reject) => {
    setTimeout(resolve, ms)
  })
}

!async function() {
  for (let i = 0; i < arr.length - 1; i++) {
    for (let j = 0; j < arr.length - i; j++) {
      const left  = arr.at(j);
      const right = arr.at(j + 1);

      if (left > right) {
        console.log(`swap ${j} ${j + 1}`)
        arr[j]     = right;
        arr[j + 1] = left;
      }
      await sleep(1);
    }
  }
}()
