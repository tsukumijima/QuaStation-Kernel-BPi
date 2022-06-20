
# QuaStation-Kernel

[Banana Pi W2](https://wiki.banana-pi.org/Banana_Pi_BPI-W2) 向けの Linux カーネル (BSP: Board Support Package) 、[BPI-W2-bsp](https://github.com/BPI-SINOVOIP/BPI-W2-bsp) の [v1.1](https://github.com/BPI-SINOVOIP/BPI-W2-bsp/releases/tag/w2-4.9-v1.1) をベースに、Qua Station 向けの変更を行った Linux カーネルです。

## BPI-W2-bsp からの変更点

- Qua Station 向けには不要な U-Boot 関連のコードやファイルを削除
- ビルドスクリプトから Qua Station 向けには不要な処理を削除
- ビルドしたカーネルやカーネルモジュールを `usbflash/bootfs/`・`usbflash/rootfs/` 以下に出力するように変更
- v1.0 → v1.1 の更新で削除された phoenix コード (Realtek 製のドライバ群？) のうち、Qua Station で利用可能な mali (GPU)・RTL8812AE・RTL8192EE のドライバを復元し、ビルドされるように変更
- v1.0 → v1.1 の更新で Qua Station との互換性がなくなった Device Tree Source (.dts) を v1.0 のソースコードに復元
- Linux カーネルのビルド設定で Bluetooth HCI UART Driver・RTK Fan Driver・RTK Video Engine 3 Codec を有効化

### Bluetooth HCI UART Driver

Realtek の三線式 (？) に対応した UART 接続の Bluetooth IC 向け Bluetooth ドライバのこと。  
Mainline の Linxu カーネルにも Bluetooth HCI UART Driver は含まれているが、これに Realtek の Bluetooth IC 向けの魔改造が行われたものらしい。

Qua Station に搭載されている RTL8761ATV には、別途 [rtkbt](https://github.com/radxa/rtkbt) から入手したファームウェアを `/lib/firmware` 以下に配置することで対応できる（はず）。

事前に [rtk_hciattach](https://github.com/radxa/rtkbt/tree/main/uart/rtk_hciattach) をビルド・インストールした上で `/usr/bin/rtk_hciattach -n -s 115200 /dev/ttyS1 rtk_h5` を実行すれば、RTL8761ATV と BlueZ スタックが接続される。

……はずなのだが、現状 `Realtek Bluetooth WARN: OP_H5_SYNC Transmission timeout` と表示されるのみで、うまく RTL8761ATV と接続できていない。  
おそらく `/dev/ttyS1` のパス指定が誤っているか、Device Tree Blob に含まれていないなどの理由で、シリアルポートそのものが認識されていないと思われる。

### RTK Fan Driver

Realtek SoC 向けのファン用ドライバのこと。

有効にはしてあるが、排気口から風が出てこないことから、実際に機能しているのかはかなり微妙。  
一応モーターの回る音はするが、もしかすると HDD の稼働音の聞き間違いかもしれない…。

### RTK Video Engine 3 Codec

Realtek SoC 向けの映像コーデックのハードウェアアクセラレーションエンジンのドライバらしい。

ソースコードを見る限り映像のハードウェアデコードに利用されているようだが、実際はプロプライエタリでクローズドソースな libOMX.*.so や libRMA.so などが実質的なドライバとなっていて、このドライバはあくまで低レイヤーかつ最低限の API 実装にとどまっている印象。  
単にこの設定を有効にしただけでは OpenMAX は動作しない。

これがないと HW エンコードができないらしいのだが、そもそも現状 HW エンコードに成功していないこと、Linux カーネルの Makefile で `incompatible-pointer-types` を常にエラーにする設定をコメントアウトしないとビルドが通らないことから、機能しているのかはよく分からない。

## ビルド

事前に Docker が使える環境であることが前提です。

> これらのコード群は GCC 9 系以下向けに書かれているため、GCC 10 以降がインストールされている環境では一部のビルドに失敗します。  
> こうした環境依存の問題を回避するため、Docker コンテナ上でビルドを行っています。  
> なお、Docker コンテナには GCC 5 系がインストールされています。

```bash
git clone https://github.com/tsukumijima/QuaStation-Kernel.git
cd QuaStation-Kernel
```

QuaStation-Kernel を clone します。

```bash
docker pull sinovoip/bpi-build-linux-4.4:ubuntu16.04
docker run -v `pwd`:/build -t -i sinovoip/bpi-build-linux-4.4:ubuntu16.04 /bin/bash
```

Banana Pi の開発元である Sinovoip が用意している Docker イメージを pull したあと、Docker コンテナの中に入ります。  
通常の Ubuntu 16.04 LTS の Docker イメージをカスタムしても良いでしょう。  

```bash
apt install -y kmod
cd /build
./build.sh 1
exit
```

Docker コンテナ内に入ったあと、Linux カーネルをビルドします。  
上記のコマンドはすべて Docker コンテナの中で実行する必要があることに注意してください。

> `kmod` をインストールしているのは、Linux カーネルのビルド途中で `depmod` コマンドが必要になるためです。

./build.sh の引数は以下の通りです。何も引数を指定しなかった場合、以下のビルドモードのいずれかを入力するよう求められます。

```
1. Build kernel, and create a package for USB flash.
2. Build kernel only.
3. Do kernel configure (menuconfig).
4. Create a package for USB flash.
5. Clean all build.
```

ビルドが終わったら、`usbflash/` ディレクトリ以下に

- Linux カーネル (`bootfs/uImage`)
- Device Tree Blob (`bootfs/bpi-w2.dtb`)
- カーネルモジュール (`rootfs/lib/modules/4.9.119-BPI-W2-Kernel/`)
- カーネルヘッダー (`rootfs/usr/src/linux-headers-4.9.119-BPI-W2-Kernel/`)

がそれぞれ生成されています。  
各種 Linux ディストリビューションと一緒に USB メモリにコピーしてください。

その後、適切に U-Boot のコマンドを実行すれば、Qua Station 上で Linux が起動できるはずです。
