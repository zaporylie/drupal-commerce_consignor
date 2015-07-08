<?php

/**
 * @file
 * Default Consignor rules.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_consignor_default_rules_configuration() {
  $rules = array();

  $rules['commerce_consignor_create_shipment'] = entity_import('rules_config', '{ "commerce_consignor_create_shipment" : {
      "LABEL" : "Commerce Consignor: Create shipment",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "TAGS" : [ "Commerce Shipment", "Commerce Consignor" ],
      "REQUIRES" : [ "rules", "commerce_consignor", "entity" ],
      "ON" : { "commerce_order_presave" : [] },
      "IF" : [
        { "data_is" : { "data" : [ "commerce-order:status" ], "value" : "packed" } },
        { "NOT data_is" : { "data" : [ "commerce-order-unchanged:status" ], "value" : "packed" } }
      ],
      "DO" : [
        { "commerce_consignor_create_shipment" : {
            "commerce_order" : [ "commerce_order" ],
            "consignor_product" : "",
            "commerce_customer_profile" : ""
          }
        }
      ]
    }
  }');

  return $rules;
}
