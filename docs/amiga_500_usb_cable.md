# How to build your own Amiga USB power cable


The Amiga 500 joystick ports don't have enough current to power Unijoysticle.

So, it must be powered from the USB port.

You can just connect a USB cable to the Unijoysticle and plug it in your computer. That works, but requires an "external" computer.

The alternative is to power the Unijoysticle from the Amiga external disk port.


## Building the cable

![image][complete_cable]

The Amiga 500 disk drive port can provide +5v @ 250mA. More than enough for the Unijoysticle neeeds, which only requires +5v @ 100mA.


Let's go over the steps:

[complete_cable]: https://lh3.googleusercontent.com/pw/AM-JKLX1h8BIZUTdIzU6P_mC6mPDTxCe9GQnnYKjc08f4ARav_fc8LyaSBGO6SvssALuR9QEA_GPan_OuojYyjrmxiI2_TKVjC0Y9oqzdwhxdJTVpmON_ItBKkc6M-kMGRjYyp7Nyz3O_nnf_0Zb6IHo-1Q_WQ=-no

[pinout]: https://old.pinouts.ru/HD/ExtDiskAmiga_pinout.shtml

### 1. Get a USB micro cable

You probably have already a few USB micro cables. Just get one and cut it so that the you have a 25 cm (~10 inches) long cable.

You will only need the Red (+5V) and Black (Ground) cables. Feel free to cut the other 2 cables.

### DB-23 connector

The drive port is a DB-23 female. So you need a DB-23 male connector.

Unfortunately the DB-23 male connectors are rather expensive since they are no longer being manufactured at scale.

If you don't mind paying premium, you can get them from these places:

* [Ebay][ebay]
* [IComp][icomp]
* [Amiga Store][amiga_store]
* ...or [just Google them][google]

[ebay]: https://www.ebay.com/itm/23-WAY-MALE-D-PLUG-DB23-CONNECTOR-FOR-COMMODORE-AMIGA-RARE-/390415565147?_ul=IN
[icomp]: https://icomp.de/shop-icomp/en/produkt-details/product/db23-male-connector.html
[amiga_store]: https://amigastore.eu/790-db23-male-connector.html
[google]: https://www.google.com/search?q=DB-23+male+connector&oq=db-23+male+connector

### Alternative: DB-25 connector

Or you can get a DB-25 male connector from multiple vendor:

* [Aliexpress][aliexpress]

And then remove the extra pins, and bend a bit the shield:

![db25_without_pins][db25_no_pins]

[aliexpress]: https://www.aliexpress.us/item/2251832655624766.html?spm=a2g0o.order_list.order_list_main.61.24dc18027PITT9&gatewayAdapt=glo2usa&_randl_shipto=US
[db25_no_pins]: https://lh3.googleusercontent.com/pw/AL9nZEUfV8rRMBE8P6En2caIlgDeJMNkwIT1aN7swTMXvBx1reyQ19fGjeddPHy1q9Ka-0MnwCPwEynLb6bZZO9m3qNH_JTYUqFank33AgKXYHFHOR-uT4sBgsYyB-lLu65X8jGfaw9A-K1CbB94wN3rEx2XFw=-no

### Solder

And now get a soldering iron and solder:


```
USB +5v (red cable)   <---> Amiga Drive Port pin 12
USB GND (black cable) <---> Amiga Drive Port pin 3 (or 4, or 5 or 6 or 7... and are GNDs)
```

The complete pinout is here: [Amiga external drive pinout][pinout]

And it should look like this:

![soldered][soldered]


[soldered]: https://lh3.googleusercontent.com/pw/AL9nZEVJqSWg3jRuoEu66gHtM16H6VYkCUCaObHsAdmCjlbFFx4CG276pd-iMZVlrtooP63-sppP_1knTVFmUVzJNsj0pn1rfys5hGINAxZd2pApwRrDgATPQoVse7Y3ZLiGVbUk_Gs5ym0MHflICT7X5MsEYg=-no
