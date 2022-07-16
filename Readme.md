
# QuaStation-Kernel-BPi

[Banana Pi W2](https://wiki.banana-pi.org/Banana_Pi_BPI-W2) 向けの BSP (Board Support Package) 版 Linux カーネル 、[BPI-W2-bsp](https://github.com/BPI-SINOVOIP/BPI-W2-bsp) の [v1.1](https://github.com/BPI-SINOVOIP/BPI-W2-bsp/releases/tag/w2-4.9-v1.1) をベースに、Qua Station 向けの様々な改良を行った Linux カーネルです。

Linux カーネルのバージョンは 4.9.119 ですが、mainline のカーネルと比較すると、Realtek SoC 向けの大幅なカスタマイズ（ Realtek SoC 固有のドライバやデバイスツリーの追加など）が行われています。  

## 既知の問題

- **USB 3.0 ポートに接続した USB メモリが USB 2.0 (480Mbps) として認識される。**
  - QuaStation-Kernel (実機に搭載されているものに近い 4.1.17 カーネル) では、正常に 5Gbps の USB 3.0 ポートとして認識されることを確認しています。
  - `lsusb -tv` や起動時のログを見る限りは USB 2.0 で接続されてしまっているように見えますが、実際にどちらで接続されているのかは分かりません。
  - せっかく USB 3.0 ポートなのに USB 2.0 接続されてしまっているのはなんとかしたいところですが、今の所原因は特定できていません。
- **シャットダウンすると、一見完全に電源が切れたように見えるものの、数十秒後にカーネルパニックが発生する。**
  - エラーメッセージに `Attempted to kill init!` とあることから、シャットダウンプロセスは完了したものの、ボードの電源を切れていないことが考えられます。
  - Android 実機の Qua Station では、eMMC 内の U-Boot の環境変数領域にある PowerStatus フラグを off に書き換えた後に「再起動」する挙動になっているあたり、Qua Station はボード自体の電源オフに対応していないのかもしれません。
  - Qua Station の eMMC に内蔵されている U-Boot は Qua Station 向けにカスタマイズされており、環境変数の PowerStatus フラグ (環境変数は `env print` で確認できる) が off になっている場合はブート処理を行わず、PowerStatus が on になるまで待機するようになっています。
  - Android 実機の Qua Station には `factory` という U-Boot の環境変数を Linux 側から読み書きするためのコマンドが同梱されています。ただ残念ながらソースコードが公開されておらず、Android 向けの実行ファイルのため実行することもできません。
    - 一般的な U-Boot であれば環境変数を `fw_printenv` / `fw_setenv` コマンドで読み書きすることができるはずですが、現状動作していません…。
    - eMMC を dd でダンプするなどして強引に読み取ることはできますが、書き込みには CRC32 と思われる環境変数すべてのハッシュ値を環境変数の保存領域 (env.txt) の先頭にセットする必要があるようで、難易度がかなり高いです。
    - Qua Station の U-Boot の環境変数を Linux から読み書きすることに成功した方は、ぜひご一報いただけると助かります。eMMC からダンプしたデータは [こちら](https://github.com/tsukumijima/Storehouse/releases/tag/Storehouse) にあります。

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
