<?php

/**
 * @file
 * Settings form.
 */

/**
 * Admin settings form.
 */
function commerce_consignor_settings_form($form) {

  $form['commerce_consignor_server'] = array(
    '#type' => 'textfield',
    '#title' => t('Server'),
    '#default_value' => variable_get('commerce_consignor_server', 'http://consignorsupport.no/ship/ShipmentServerModule.dll'),
  );

  $form['commerce_consignor_actor'] = array(
    '#type' => 'textfield',
    '#title' => t('Actor'),
    '#default_value' => variable_get('commerce_consignor_actor', 63),
  );

  $form['commerce_consignor_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Key'),
    '#default_value' => variable_get('commerce_consignor_key', 'sample'),
  );

  return system_settings_form($form);
}
