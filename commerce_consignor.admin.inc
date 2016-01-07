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

  $form['#validate'][] = 'commerce_consignor_settings_form_clear_cache';
  return system_settings_form($form);
}

/**
 * Clear product cache.
 */
function commerce_consignor_settings_form_clear_cache($form, $form_state) {
  cache_clear_all('_commerce_consignor_get_products', 'cache');
}