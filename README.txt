≪著作権および免責事項≫

　本ソフトはMITライセンスのもとで公開されています。LICENSE.txtをお読みください。
また、著作権は埼玉大学設計工学研究室が保有しています。

　このソフトウェアを使用したことによって生じたすべての障害・損害・不具合等に関し
ては、一切の責任を負いません。各自の責任においてご使用ください。

≪更新履歴≫
バージョン  更新日     更新内容                           
--------------------------------------------------------------------------------
1.0         2014/10/24  新規公開
1.1         2014/11/21  RTM_ORiN_Converter_CRDソースコード修正
			解説ドキュメント内容修正
			操作マニュアル内容修正
			導入マニュアル内容修正

≪はじめに≫
　本パッケージは、RTミドルウエアコンテスト2014の応募作品である「ORiNとの連携によ
る産業用ハードウエアRTCの拡充／CRDプロバイダを用いたロボット固有情報のXML化による
産業用ロボット汎用RTCの開発」を実施するためのものです。
　まずはじめに、本作品を実施するために必要なハードウエアとソフトウエアの導入手順
を示したマニュアルである「Document」フォルダ内の「ORiNとの連携によるRTMの産業機器
用ハードウエアRTCの拡充_導入マニュアル_ver_1_0.pdf」をご覧ください。

≪使用に際して≫
　本RTC(RTM_ORiN_Converter_CRD)を利用するには、ORiN2 SDKのORiNランタイムカーネル
ライセンスが必要となります。使用する際には、useORiN.h中でincludeしているCAO.h、
及びuseORiN.cpp中でincludeしているCAO_i.cのパスを設定しなおしてください。CAO.h、
CAO_i.cはORiN2 SDKのインストール先フォルダの
　　"ORiN2\CAO\Include"
に保存されています。

≪ファイル構成≫
GeneralPurposeIndustrialRobotRTC_CRD_1_1
  ├Document
  │  ├ORiNとの連携によるRTMの産業機器用ハードウエアRTCの拡充_解説ドキュメント_ver_1_1.pdf
  │  ├ORiNとの連携によるRTMの産業機器用ハードウエアRTCの拡充_操作マニュアル_ver_1_1.pdf
  │  ├ORiNとの連携によるRTMの産業機器用ハードウエアRTCの拡充_導入マニュアル_ver_1_1.pdf
  │  ├オペレーションコマンド実行RTC　操作マニュアル_ver_2_0.pdf
  │  └産業用ロボット汎用RTC 操作マニュアル_ver_1_1.pdf
  ├Movie
  │  ├動作検証実験動画(DENSO製ロボット).mp4
  │  └動作検証実験動画(YAMAHA製ロボット).mp4
  ├RTC
  │  ├bin
  │  │  ├CameraPositionCorrectionRTC
  │  │  │  ├camerapositioncorrectionrtc.dll
  │  │  │  ├camerapositioncorrectionrtc.exp
  │  │  │  ├camerapositioncorrectionrtc.lib
  │  │  │  ├camerapositioncorrectionrtc.exe
  │  │  │  └rtc.conf
  │  │  ├DIOInterfaceModuleRTC
  │  │  │  ├diointerfacemodulertc.dll
  │  │  │  ├diointerfacemodulertc.exp
  │  │  │  ├diointerfacemodulertc.lib
  │  │  │  ├diointerfacemodulertccomp.exe
  │  │  │  └rtc.conf
  │  │  ├IntegratedControlRTC
  │  │  │  ├integratedcontrolrtc.dll
  │  │  │  ├integratedcontrolrtc.exp
  │  │  │  ├integratedcontrolrtc.lib
  │  │  │  ├integratedcontrolrtccomp.exe
  │  │  │  ├PointData.txt
  │  │  │  └rtc.conf
  │  │  ├OperationCommandRTC
  │  │  │  ├operationcommandrtc.dll
  │  │  │  ├operationcommandrtc.exp
  │  │  │  ├operationcommandrtc.lib
  │  │  │  ├operationcommandrtccomp.exe
  │  │  │  ├rtc.conf
  │  │  │  └SampleFile.txt
  │  │  ├RTM_ORiN_Converter_CRD
  │  │  │  ├DENSO.xml
  │  │  │  ├rtc.conf
  │  │  │  ├rtm_orin_converter_crd.dll
  │  │  │  ├rtm_orin_converter_crd.exp
  │  │  │  ├rtm_orin_converter_crd.lib
  │  │  │  └rtm_orin_converter_crd.exe
  │  │  └TimeBooleanSeqOutRTC
  │  │      ├rtc.conf
  │  │      ├timedbooleanseqoutrtc.dll
  │  │      ├timedbooleanseqoutrtc.exp
  │  │      ├timedbooleanseqoutrtc.lib
  │  │      └timedbooleanseqoutrtccomp.exe
  │  ├script
  │  │  ├RTM_ORiN_Converter_CRDTest
  │  │  │  └rtshellによるバッチファイル
  │  │  ├DIOInterfaceModuleRTCTest
  │  │  │  └rtshellによるバッチファイル
  │  │  ├PartialEdgeCompTest1
  │  │  │  └rtshellによるバッチファイル
  │  │  ├PartialEdgeCompTest2
  │  │  │  └rtshellによるバッチファイル
  │  │  ├PickandPlace
  │  │  │  └rtshellによるバッチファイル
  │  │  ├32bit_PreparationForRTCsEXE.bat
  │  │  ├64bit_PreparationForRTCsEXE.bat
  │  │  └host.bat
  │  └src
  │      ├CameraPositionCorrectionRTC
  │      │  └ソースファイルなど
  │      ├DIOInterfaceModuleRTC
  │      │  └ソースファイルなど
  │      ├IntegratedControlRTC
  │      │  └ソースファイルなど
  │      ├OperationCommandRTC
  │      │  └ソースファイルなど
  │      ├RTM_ORiN_Converter_CRD
  │      │  └ソースファイルなど
  │      └TimeBooleanSeqOutRTC
  │          └ソースファイルなど
  ├LICENSE.txt
  └README.txt