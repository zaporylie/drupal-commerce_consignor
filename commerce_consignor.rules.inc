<?php

/**
 * @file
 * Rules integration for Commerce Nets module.
 */

/**
 * Implements hook_rules_action_info().
 */
function commerce_consignor_rules_action_info() {
  $actions = array();

  $actions['commerce_consignor_create_shipment'] = array(
    'label' => t('Create shipment.'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Apply created shipment to an order'),
      ),
      'consignor_product' => array(
        'type' => 'integer',
        'label' => t('Consignor Product'),
        'options list' => 'commerce_consignor_products_options_list_flatten',
        'restriction' => 'input',
      ),
      'commerce_customer_profile' => array(
        'type' => 'commerce_customer_profile',
        'label' => t('Get sender address.'),
        'optional' => TRUE,
      ),
    ),
    'group' => t('Commerce Shipping'),
    'callbacks' => array(
      'execute' => 'commerce_consignor_rules_create_shipment',
    ),
  );

  return $actions;
}

/**
 * Create new shipment with Consignor API.
 *
 * @param object $order
 *   Order object - from rules.
 * @param int $consignor_product
 *   Consignor product ID - from rules.
 * @param int|null $customer
 *   Customer object - from rules.
 *
 * @return bool
 *   FALSE if order cannot be created.
 */
function commerce_consignor_rules_create_shipment($order, $consignor_product, $customer = NULL) {

  if (isset($order->data['commerce_consignor']['shipment_id']) && $order->data['commerce_consignor']['shipment_id']) {
    return TRUE;
  }

  $data = array(
    'ProdConceptID' => intval($consignor_product),
  );
  if (!empty($customer)) {
    // @todo Add sender from customer profile.
  }
  $shipment_id = commerce_consignor_create_shipment($order, $data);
  if (empty($shipment_id)) {
    watchdog('commerce_consignor', 'Unable to create shipment label in Consignor.', array(), WATCHDOG_WARNING);
    drupal_set_message(t('Unable to create shipment label in Consignor.'), 'warning');
    return FALSE;
  }
  if (!isset($order->data['commerce_consignor'])) {
    $order->data['commerce_consignor'] = array();
  }
  $order->data['commerce_consignor']['shipment_id'] = $shipment_id;
}
