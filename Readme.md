
# QuaStation-Kernel-BPi

[Banana Pi W2](https://wiki.banana-pi.org/Banana_Pi_BPI-W2) 向けの Linux カーネル (BSP: Board Support Package) 、[BPI-W2-bsp](https://github.com/BPI-SINOVOIP/BPI-W2-bsp) の [v1.1](https://github.com/BPI-SINOVOIP/BPI-W2-bsp/releases/tag/w2-4.9-v1.1) をベースに、Qua Station 向けの様々な改良を行った Linux カーネルです。

## カーネルのビルド

事前に Docker が使える環境であることが前提です。

> これらのコード群は GCC 9 系以下向けに書かれているため、GCC 10 以降がインストールされている環境では一部のビルドに失敗します。  
> こうした環境依存の問題を回避するため、Docker コンテナ上でビルドを行っています。  
> なお、Docker コンテナには GCC 7 系がインストールされています。

```bash
git clone https://github.com/tsukumijima/QuaStation-Kernel-BPi.git
cd QuaStation-Kernel-BPi
```

QuaStation-Kernel-BPi を clone します。

```bash
make docker-image
```

事前に、ビルドで使う Docker イメージをビルドしておきます。

```bash
make build
```

あとは `make build` を実行するだけで、全自動でカーネルのビルドが行われます。  

PC のスペックにもよりますが、カーネルのビルドには少し時間がかかります。  
`Kernel build is completed.` と表示されたら完了です！

`make config` で、カーネル構成 (.config) を調整できます。  
既定で Qua Station 向けに最適化された defconfig が適用されています。基本的に調整する必要はありません。

`make clean` で、ビルドされた成果物（ビルドキャッシュなど）をすべて削除できます。  
最初からすべてビルドし直したい際などに実行します。

## 成果物

ビルドが終わると、`usbflash/` ディレクトリ以下に

- Linux カーネル (`bootfs/uImage`)
- Device Tree Blob (`bootfs/QuaStation.dtb`)
- カーネルモジュール (`rootfs/usr/lib/modules/4.9.119-quastation/`)
- カーネルヘッダー (`rootfs/usr/src/linux-headers-4.9.119-quastation/`)

がそれぞれ生成されています。  

`usbflash/rootfs/` 以下には、他にも Bluetooth のファームウェア (rtlbt) や OpenMAX ライブラリなどのビルド済みバイナリが配置されています。  
各種 Linux ディストリビューションと一緒に USB メモリにコピーしてください。

その後、適切に U-Boot のコマンドを実行すれば、Qua Station 上で Linux が起動できるはずです。
