# sensor_tag
sensor_tag��һ�������������򣬼����Խ�Ӳ���ϵĴ��������ݷ��͸��ֻ�������ͨ���ֻ����۲촫���������ݱ仯��

### Ч��չʾ



![](./images/st1.png)![](./images/st2.png)![](./images/st3.png)

��Ӧ��android�˳������Ч��չʾ��

��Ƶ���ӣ�
[http://v.qq.com/boke/page/w/0/x/w0198p4nnhx.html](http://v.qq.com/boke/page/w/0/x/w0198p4nnhx.html)

���������
[http://www.52cannon.com/bbs/forum.php?mod=viewthread&tid=254&highlight=sensor](http://www.52cannon.com/bbs/forum.php?mod=viewthread&tid=254&highlight=sensor)

### �������̽���


�����Ҫ����һ�´������̣�

```
1. ϵͳ����(����`ϵͳAPI`��Ҳ��Ӧ�ò��̵ĵ�һ���(ϵͳ�ص��¼�)���൱�ڴ�ͳ��`main()`������) -- on_ready��
2. ����Cannon�������㲥��ַ -- ble_set_adv_param��
3. Cannon��ʼ�����㲥 -- ble_device_start_advertising��
4. �ֻ���APP��Cannon�������ӣ�����ʹ��BLE��������APP��
5. BLE��������APP��Cannon��һЩ���ݣ�
6. Cannon�յ����ݺ󣬴����ص��¼� -- ble_device_on_message��
7. Cannon������ԭ�ⲻ���Ļش����ֻ� -- ble_device_send��
8. �ֻ���Cannon�Ͽ����ӣ�
9. Cannon�����Ͽ������¼� -- ble_device_on_disconnect��
10. Cannon���¿��������㲥 -- ble_device_start_advertising��

```

> ���ס���շ��������ݣ���Ҫ��Ҫ�������ӣ����������ӣ���Ҫ�豸�ȿ����㲥��


### ��

API�ĵ���
[http://www.juma.io/doc/zh/embedded_api/task/](http://www.juma.io/doc/zh/embedded_api/task/)

���л����İ�װָ����
[http://www.juma.io/doc/zh/stm32_platform/cannon_env/](http://www.juma.io/doc/zh/stm32_platform/cannon_env/)

���������
[http://www.juma.io/](http://www.juma.io/)

������̳��
[http://www.52cannon.com/bbs/forum.php](http://www.52cannon.com/bbs/forum.php)

����1000�˽���Ⱥ��
QQ��271927055

���빫�ںţ�
![](./images/1.jpg)