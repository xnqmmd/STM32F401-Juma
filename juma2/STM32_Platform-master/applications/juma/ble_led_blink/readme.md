# ble_led_blink
ble_led_blink��һ������Ӳ����LED��ʾ����˸��demo��

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